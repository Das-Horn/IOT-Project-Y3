import React from "react";
import styles from "../SCSS/HomePage.module.scss";
import Graph from "./GraphV2";
import Intro from "./Intro";
import Button from "./Button";
import Tgl from "./ToggleInd";

import { v4 as uuidv4 } from 'uuid';


export default class HomePage extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            Loading : true,
            LoadingButton : true,
            Buttons : null
        }
    }

    async componentDidMount(){
        const UName = window.sessionStorage.getItem('UName');
        const Pass = window.sessionStorage.getItem('Pass');
        //Load Page content
        const Lgin = await fetch(`/api/Login/${UName}/${Pass}`).then(
            (res) => res.json()
        );
        console.log(Lgin);
        if(Lgin.login){
            this.setState({
                Loading : false
            })
        }else{
            window.location.replace('/');
        }

        //Load Buttons and watchers
        const Btn = await fetch('/api/Requests/jobs').then(
            (res) => res.json()
        )
        const Sen = await fetch('/api/Requests/Sensors').then(
            (res) => res.json()
        )
        var Name;
        var TempArray = [];
        for (let i = 0; i < Btn.length; i++) {
            const ButtonVal = Btn[i];
            for (let i = 0; i < Sen.length; i++) {
                const Sensor = Sen[i];
                if(ButtonVal.SensorID === Sensor.SensorID){
                    Name = Sen[i].Sensors;
                    console.log(Name);
                    if(ButtonVal.readOnly == false){
                        TempArray.push(<Button key={uuidv4()} sensID={ButtonVal.SensorID}>{Name}</Button>);
                    }else{
                        TempArray.push(<Tgl key={uuidv4()} sensID={ButtonVal.SensorID}>{Name}</Tgl>);
                    }
                    break;
                }
            }
        }
        this.setState({
            LoadingButton : false,
            Buttons : TempArray
        });

    }

    render() {
        console.log(this.state.Buttons)
        if(this.state.Loading){
            return(
                <div className={styles.Loading}><div className={styles.ripple}><div></div><div></div></div></div>
            );
        }else{
            return(
                <div className={styles.Done}>
                    <div className={styles.graphCont}>
                        <Intro>
                            <div className={styles.centerGraph}>
                                <Graph MCDat="Requests/MCList" xTag="Requests/Data/Temp"/>
                            </div>
                            <p className="centerText">Above is a simple graph to show tempature over time. The graph can differentiate between multiple devices and select data relating to that device.</p>
                        </Intro>
                    </div>
                    <div className={styles.buttonCont}>
                        {this.state.LoadingButton ? <div className={styles.ripple}><div>    </div><div> </div></div> : this.state.Buttons}
                    </div>
                </div>
            );
        }
    }
}