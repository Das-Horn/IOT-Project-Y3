import styles from '../../styles/Graphs.module.css';
import React from "react";
import * as d3 from 'd3';

class BinGraph extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            data : null,
            names : null,
            counter : 0
        };
        this.x;
        this.line;
        this.y;
        this.myColor;
        this.wait = true;
        this.focus;
        this.focusText;
    }

    componentDidMount(){
        d3.json('/api/getName').then( (data) => {
            console.log(data);
            this.setState({names : data});
            this.wait = false;
        }).catch((any) => {

        }).then(() => {
        d3.json('/api/getTimes').then( (data) => {
            console.log(data);
            this.setState({data : data});
            this.createGraph();
        })});
        setInterval(() => {
            this.getData();
        }, 10000);
        // Listen to the slider?
        d3.select("#selectButton").on("change", (d) => {
            let selectedGroup = document.querySelector('#selectButton').value
            this.updateChart(selectedGroup)
        });
    }

    getData() {
        d3.json('/api/getName').then( (data) => {
            console.log(data);
            this.setState({names : data});
            this.wait = false;
        }).catch((any) => {

        }).then(() => {
        d3.json('/api/getTimes').then( (data) => {
            console.log(data);
            this.setState({data : data});
            let selectedGroup = document.querySelector('#selectButton').value;
            this.updateChart(selectedGroup);
        })});
    }

    render(){
        return(
            <div className={styles.BinGraphMainCont}>
                <select id={"selectButton"}></select>
                <div id={"Graph"} className={styles.BinGraphSubCont}>

                </div>
            </div>
        );
    }

    async createGraph(){
        console.log(`Begining Graph generation.`);
        // set the dimensions and margins of the graph
        const margin = {top: 30, right: 30, bottom: 30, left: 50},
        width = 460 - margin.left - margin.right,
        height = 400 - margin.top - margin.bottom;

        // append the svg object to the body of the page
        const svg = d3.select("#Graph")
        .append("svg")
        .attr("width", width + margin.left + margin.right)
        .attr("height", height + margin.top + margin.bottom)
        .append("g")
        .attr("transform", `translate(${margin.left},${margin.top})`);

        // get the data
        let data = this.state.data.slice(Math.max(this.state.data.length - 30, 0));

        // List of bin ids
        let lists = data.map(a => a.bin_id);
        let checker = new Array;
        for (let i = 0; i < lists.length; i++) {
            if(!checker.includes(lists[i])){
                checker += lists[i];
            }
            // console.log(checker);
        }
        lists = checker;
        console.log(`lists = \t ${lists}`);

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
                    if(this.state.names[i].id == d){
                        final = this.state.names[i].name;
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
            return this.getMinute(d.entry_time)
        }))
        .range([ 0, width ]);
        svg.append("g")
        .attr("transform", `translate(0, ${height})`)
        .call(d3.axisBottom(this.x).ticks(7));

        // Add Y axis
        this.y = d3.scaleLinear()
        .domain([0, 100])
        .range([ height, 0 ]);
        svg.append("g")
        .call(d3.axisLeft(this.y));

        // Initialize line with first group of the list
        this.line = svg
        .append('g')
        .append("path")
            .datum(data.filter((d) => {return d.bin_id == parseInt(document.querySelector('#selectButton').value)}))
            .attr("d", d3.line()
            .x((d) => { return this.x(this.getMinute(d.entry_time)) })
            .y((d) => { return this.y(+d.perc_filled) })
            .curve(d3.curveBasis)
            )
            .attr("stroke", (d) => { return this.myColor("valueA") })
            .style("stroke-width", 4)
            .style("fill", "none");

            // code for mouse over stats
              // Create the circle that travels along the curve of chart
            this.focus = svg
            .append('g')
            .append('circle')
                .style("fill", "none")
                .attr("stroke", "black")
                .attr('r', 8.5)
                .style("opacity", 0);

            // Create the text that travels along the curve of chart
            this.focusText = svg
            .append('g')
            .append('text')
                .style("opacity", 0)
                .attr("text-anchor", "left")
                .attr("alignment-baseline", "middle");

            svg
            .append('rect')
            .style("fill", "none")
            .style("pointer-events", "all")
            .attr('width', width)
            .attr('height', height)
            .on('mouseover', () => {
                this.focus.style("opacity", 1);
                this.focusText.style("opacity",1);
            })
            .on('mousemove', () => {
                let data = this.state.data
                // recover coordinate we need
                console.log(d3.pointer(Event));
                var x0 = this.x.invert(d3.pointer(Event)[0]);
                var i = d3.bisect(data, x0, 1);
                var selectedData = data[i]
                console.log(`Debug Data for mousemove:\nx0: ${x0}\ni: ${i}\ndata : ${data}\n selectedData : ${selectedData}`)
                this.focus
                  .attr("cx", this.x(selectedData.entry_time))
                  .attr("cy", this.y(selectedData.perc_filled))
                this.focusText
                  .html("Filled:" + selectedData.entry_time + "\n" + "Date:" + selectedData.perc_filled)
                  .attr("x", this.x(selectedData.entry_time)+15)
                  .attr("y", this.y(selectedData.perc_filled))
            })
            .on('mouseout', () => {
                this.focus.style("opacity", 0)
                this.focusText.style("opacity", 0)
            });
    }

      //updating the graph
      updateChart(selectedGroup) {  
        const margin = {top: 30, right: 30, bottom: 30, left: 50}
        const width = 460 - margin.left - margin.right;
        let data = this.state.data.slice(Math.max(this.state.data.length - 30, 0));
      // Create new data with the selection?
      console.log(selectedGroup);
      const dataFilter = data.filter((d) => {return d.bin_id == parseInt(selectedGroup)})

      this.x = d3.scaleTime()
      .domain(d3.extent(data, (d) => { 
          return this.getMinute(d.entry_time)
      }))
      .range([ 0, width ]);


      // Give these new data to update line
      this.line
          .datum(dataFilter)
          .transition()
          .duration(1000)
          .attr("d", d3.line()
            .x((d) => { return this.x(this.getMinute(d.entry_time)) })
            .y((d) => { return this.y(+d.perc_filled) })
            .curve(d3.curveBasis)
          )
          .attr("stroke", (d) =>{ return this.myColor(selectedGroup) })
        //   .style("fill", (d) =>{ return this.myColor(selectedGroup) })
      }

      getMinute(d){
        let Final;
        let temp = d.split(/[-:TZ]/);
        var format = d3.timeFormat("%x")
        Final = new Date(Date.UTC(temp[0],temp[1]-1,temp[2],temp[3],temp[4],temp[5])).getTime();
        console.log(format(Final));
        // return format(Final);
        return Final;
      }
}

export default BinGraph;