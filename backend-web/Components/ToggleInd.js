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
        // setInterval();
    }

    render() {
        return(
            <div className={this.state.tgl ? styles.Green : styles.Red}>
                <p>{this.props.children}</p>
            </div>
        );
    }
}