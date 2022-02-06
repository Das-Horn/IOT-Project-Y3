import React from "react";
import styles from "../SCSS/TGL.module.scss";

export default class Tgl extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tgl : this.props.initState != null ? this.props.initState : false,
            sensID : this.props.sensID != null ? this.props.sensID : 1,
            loaded : false
        }
        this.fetchData = this.fetchData.bind(this);
        this.myInterval;
    }

    componentDidMount() {
        this.myInterval = setInterval(this.fetchData, 5000);
    }

    fetchData() {
        fetch(`/api/Requests/jobs`)
        .then(
            (res) => res.json()
        )
        .then((res) => {
            // console.log(res);
            var resp;
            for (let i = 0 ; i < res.length; i++) {
                // console.log(i)
                if(res[i]['SensorID'] == this.state.sensID){
                    resp = res[i]['Action'] == 1 ? true : false;
                }
            }
            this.setState({
                tgl : resp
            });
        })
        .catch(function(res) {
            console.warn(`[Toggle indicator] Unable to get data from api.`);
            console.log(res);
        })
        // .finally(() => this.forceUpdate())
    }

    componentWillUnmount(){
        clearInterval(this.myInterval)
    }

    parseData(res){

    }

    render() {
        return(
            <div className={this.state.tgl ? styles.Green : styles.Red}>
                <p>{this.props.children}</p>
            </div>
        );
    }
}