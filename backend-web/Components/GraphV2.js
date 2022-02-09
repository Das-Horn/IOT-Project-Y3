import styles from '../SCSS/Graph.module.scss';
import React from "react";
import Chart from 'chart.js/auto';
import 'chartjs-adapter-luxon';
import * as Utils from './Scripts/Utils';
import {DateTime} from 'luxon';

class Graph extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            Tempdata : null,
            Humidata : null,
            names : null,
            nameList : null,
            MC : 1
        };
        this.myInterval;
        this.TempGraph;
    }

    async componentDidMount(){
        await this.getData();
        this.createChart();
    }

    async getData(){ // A method to gather the types of data needed
        const Temp = await fetch('/api/Requests/Data/Temp').then(
            (res) => res.json()
        ).then(
            (res) => {
                const mapped = res.map(obj => {
                    let rObj = {};
                    rObj.x = DateTime.fromFormat(obj.TimeStamp.replace('T', ' ').replace('Z', ''), "yyyy-MM-dd HH:mm:ss.SSS");
                    rObj.y = obj.Data;
                    return rObj
                })
                return mapped
            }
        );

        const Humid = await fetch('/api/Requests/Data/Humid').then(
            (res) => res.json()
        ).then(
            (res) => {
                const mapped = res.map(obj => {
                    let rObj = {};
                    rObj.x = DateTime.fromFormat(obj.TimeStamp.replace('T', ' ').replace('Z', ''), "yyyy-MM-dd HH:mm:ss.SSS"); //Mysql Date filtering
                    rObj.y = obj.Data;
                    return rObj
                })
                return mapped
            }
        );

        const Names = await fetch('/api/Requests/MCList').then(
            (res) => res.json()
        );

        this.setState({
            Tempdata : Temp,
            Humidata : Humid,
            names : Names
        })
        
        this.createMCList();
    }

    createChart(){ // Create graph chart
        const ctx = document.querySelector('#myChart');
        // ^ gets the canvas
        
        //create datasets and configurations
        const data = {
            datasets: [
                {
                    label: 'Tempature (C)',
                data: this.state.Tempdata,
                borderColor: Utils.CHART_COLORS.red,
                backgroundColor: Utils.transparentize(Utils.CHART_COLORS.red, 0.5),
                },
                {
                    label: 'Humidity (%)',
                data: this.state.Humidata,
                borderColor: Utils.CHART_COLORS.blue,
                backgroundColor: Utils.transparentize(Utils.CHART_COLORS.blue, 0.5),
                }
            ]
        };
        const config = {
            type: 'line',
            data: data,
            options: {
            responsive: true,
            maintainAspectRatio : false,
            responsiveAnimationDuration : 20,
            plugins: {
                legend: {
                position: 'top',
                },
                title: {
                display: true,
                text: 'Tempature & Humidity'
                }
            },
            scales: {
                x: {
                    type: 'time',
                    time: {
                      // Luxon format string
                      tooltipFormat: 'DD T'
                    },
                    title: {
                      display: true,
                      text: 'Date'
                    }
                  },
                  y: {
                    title: {
                      display: true,
                      text: 'Tempature / Humidity'
                    }
                  }
                }
            },
        };
        this.TempGraph = new Chart(ctx, config);
    }

    async createMCList(){
        let Buffer = [];
        for (let i = 0; i < this.state.names.length; i++) {
            const Data = [this.state.names[i].MCName, this.state.names[i].MCKey];
            Buffer.push(<option key={new Date().valueOf()} value={Data[1]}>{Data[0]}</option>);
        }
        this.setState({
            nameList : Buffer
        })
        console.log(Buffer);
    }

    componentWillUnmount(){
          clearInterval(this.myInterval);
        }
    //Render Method
    render(){
        return(
            <div className={styles.GraphMainCont}>
                <select className={styles.input} id={"selectButton"}>
                    {this.state.nameList ? this.state.nameList : <option>loading...</option>}
                </select>
                <div className={styles.GraphSubCont}>
                    <canvas id="myChart" width={"300px"} height={"360px"}></canvas>
                </div>
            </div>
        );
    }
}

export default Graph;