import React from "react";
import styles from "../SCSS/TGL.module.scss";

export default class Tgl extends React.Component {
    constructor(props) {
        super(props);
        this.state = {
            tgl : this.props.initState != NaN ? this.props.initState : false
        }
    }

    componentDidMount() {
        setInterval(this.fetchData, 2000);
    }

    fetchData() {
        fetch(`/api/`+ this.props.api != null ? this.props.api : 'Requests/Sensors')
        .then((res) => {
            this.setState({
                tgl : res
            });
        })
        .catch((res) => {
            console.warn(`[Toggle indicator] Unable to get data from api.`);
        })
        .finally( () => {
            this.forceUpdate();
        })
    }

    render() {
        return(
            <div className={this.state.tgl ? styles.Green : styles.Red}>
                <p>{this.props.children}</p>
            </div>
        );
    }
}