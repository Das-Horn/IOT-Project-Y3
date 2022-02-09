import styles from '../SCSS/Graph.module.scss';
import React from "react";
import * as d3 from 'd3';

class Graph extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            data : null,
            names : null,
            counter : 0,
            category : 'Temp'
        };
        this.x;
        this.line;
        this.y;
        this.myColor;
        this.wait = true;
        this.focus;
        this.focusText;
        this.myInterval;
    }

    componentDidMount(){
        d3.json('/api/'+this.props.MCDat).then( (data) => {
            this.setState({names : data});
            this.wait = false;
        }).catch((any) => {
            console.error(`[Graph component] an error has occurred fetching data.`)
        }).then(() => {
        d3.json('/api/'+this.props.xTag).then( (data) => {
            this.setState({data : data});
            this.createGraph();
        })});
        this.myInterval = setInterval(() => {
            this.getData();
        }, this.props.interval != null ? this.props.interval : 10000); //Allow Adjustmant per graph with a default value
        // Listen to the selector
        d3.select("#selectButton").on("change", (d) => {
            let selectedGroup = document.querySelector('#selectButton').value
            this.updateChart(selectedGroup)
        });

        // Create
    }

    getData() {
        d3.json('/api/'+this.props.MCDat).then( (data) => {
            this.setState({names : data});
            this.wait = false;
        }).catch((any) => {
            console.log(any)
        }).then(() => {
        d3.json('/api/'+this.props.xTag).then( (data) => {
            this.setState({data : data});
            let selectedGroup = document.querySelector('#selectButton').value;
            this.updateChart(selectedGroup);
        })});
    }

    render(){
        return(
            <div className={styles.GraphMainCont}>
                <select className={styles.input} id={"selectButton"}></select>
                <div id={"Graph"} className={styles.GraphSubCont}>

                </div>
            </div>
        );
    }

    async createGraph(){
        console.log(`Begining Graph generation.`);
        // set the dimensions and margins of the graph
        const margin = {top: 30, right: 30, bottom: 30, left: 50},
        width = 350 - margin.left - margin.right,
        height = 300 - margin.top - margin.bottom;

        // append the svg object to the body of the page
        const svg = d3.select("#Graph")
        .append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", `translate(${margin.left},${margin.top})`);

        // get the data
        let data = this.state.data.slice(Math.max(this.state.data.length - 30, 0));

        // List of Microcontrolllers
        let lists = data.map(a => a.MC); // adapt this once clearer data format determined
        let checker = new Array;
        for (let i = 0; i < lists.length; i++) {
            if(!checker.includes(lists[i])){
                checker += lists[i];
            }
        }
        lists = checker;

        // add the options to the button
        d3.select("#selectButton")
        .selectAll('myOptions')
        .data(lists)
        .enter()
        .append('option')
        .text((d) => {  //uses text instead of bin name if available
            let final;
            if(this.state.names != null){
                for (let i = 0; i < this.state.names.length; i++) {
                    if(this.state.names[i].MCKey == d){
                        final = this.state.names[i].MCName;
                        break;
                    }
                    final = d;
                }
            } else {
                let final = d;
            }
            return final;
             }) // text showed in the menu
        .attr("value", (d) => { return d; }) // corresponding value returned by the button

        // A color scale: one color for each group
        this.myColor = d3.scaleOrdinal()
        .domain(lists)
        .range(d3.schemeSet2);

        // Add X axis --> it is a date format
        this.x = d3.scaleTime()
        .domain(d3.extent(data, (d) => { 
            return this.getMinute(d.TimeStamp)
        }))
        .range([ 0, width ]);
        svg.append("g")
        .attr("transform", `translate(0, ${height})`)
        .call(d3.axisBottom(this.x).ticks(7));

        // Add Y axis
        this.y = d3.scaleLinear()
        .domain([-10, 50])
        .range([ height, 0 ]);
        svg.append("g")
        .call(d3.axisLeft(this.y));

        // Initialize line with first group of the list
        this.line = svg
        .append('g')
        .append("path")
            .datum(data.filter((d) => {return d.MC == parseInt(document.querySelector('#selectButton').value)}))
            .attr("d", d3.line()
            .x((d) => { return this.x(this.getMinute(d.TimeStamp)) })
            .y((d) => { return this.y(+d.Data) })
            .curve(d3.curveBasis)
            )
            .attr("stroke", (d) => { return this.myColor("valueA") })
            .style("stroke-width", 4)
            .style("fill", "none");
    }

      //updating the graph
      updateChart(selectedGroup) {  
        const margin = {top: 30, right: 30, bottom: 30, left: 50}
        const width = 460 - margin.left - margin.right;
        let data = this.state.data.slice(Math.max(this.state.data.length - 30, 0));
      // Create new data with the selection?
    //   console.log(selectedGroup);
      const dataFilter = data.filter((d) => {return d.MC == parseInt(selectedGroup)})

      this.x = d3.scaleTime()
      .domain(d3.extent(data, (d) => { 
          return this.getMinute(d.TimeStamp)
      }))
      .range([ 0, width ]);


      // Give these new data to update line
      this.line
          .datum(dataFilter)
          .transition()
          .duration(1000)
          .attr("d", d3.line()
            .x((d) => { return this.x(this.getMinute(d.TimeStamp)) })
            .y((d) => { return this.y(+d.Data) })
            .curve(d3.curveLinear) // Line interpolation
          )
          .attr("stroke", (d) =>{ return this.myColor(selectedGroup) })
        //   .style("fill", (d) =>{ return this.myColor(selectedGroup) })
      }

      getMinute(d){
        let Final;
        let temp = d.split(/[-:TZ]/);
        var format = d3.timeFormat("%x")
        Final = new Date(Date.UTC(temp[0],temp[1]-1,temp[2],temp[3],temp[4],temp[5])).getTime();
        // console.log(format(Final));
        // return format(Final);
        return Final;
      }

      componentWillUnmount(){
          clearInterval(this.myInterval);
      }
}

export default Graph;