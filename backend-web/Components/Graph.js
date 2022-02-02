import styles from '../SCSS/Graph.module.scss';
import React from "react";
import * as d3 from 'd3';

class Graph extends React.Component{
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
        d3.json('/api/'+this.props.MCDat).then( (data) => {
            this.setState({names : data});
            this.wait = false;
        }).catch((any) => {

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
                <select id={"selectButton"}></select>
                <div id={"Graph"} className={styles.GraphSubCont}>

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
                    if(this.state.names[i].id == d){
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
            .on('mousemove', (Event, d) => {  //Fixed mouseover thingy needed to declare event (╯°□°）╯︵ ┻━┻
                let data = this.state.data
                // recover coordinate we need
                var x0 = this.x.invert(d3.pointer(Event)[0]);
                var i = d3.bisect(data, x0, 1);
                var selectedData = data[i]
                // console.log(`Debug Data for mousemove:\nx0: ${x0}\ni: ${i}\ndata : ${data}\n selectedData : ${selectedData}`)
                console.log(this.getMinute(selectedData.TimeStamp))
                this.focus
                  .attr("cx", this.x(this.getMinute(selectedData.TimeStamp)))
                  .attr("cy", this.y(selectedData.Data))
                this.focusText
                  .html("Filled:" + selectedData.TimeStamp + "\n" + "Tempature:" + selectedData.Data)
                  .attr("x", this.x(this.getMinute(selectedData.TimeStamp))+15)
                  .attr("y", this.y(selectedData.Data))
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
        // console.log(format(Final));
        // return format(Final);
        return Final;
      }
}

export default Graph;