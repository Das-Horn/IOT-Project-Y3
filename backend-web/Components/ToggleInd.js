import React from "react";
import styles from "../SCSS/TGL.module.scss";

export default class Tgl extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tgl : this.props.initState != null ? this.props.initState : false,
            sensID : this.props.sensID != null ? this.props.sensID : 1
        }
        this.fetchData = this.fetchData.bind(this);
    }

    componentDidMount() {
        setInterval(this.fetchData, 2000);
    }

    fetchData() {
        fetch(`/api/Requests/jobs`)
        .then(
            (res) => res.json()
        )
        .then((res) => {
            let data = res;
            console.log(res);
            var resp;
            for (let i = 0 ; i < res.length; i++) {
                console.log(i)
                if(res[i]['SensorID'] == this.state.sensID){
                    console.log(`debug Action = ${res[i].Action}`)
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