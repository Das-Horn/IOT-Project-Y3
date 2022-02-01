import React from "react";
import styles from "../SCSS/Button.module.scss";

export default class Button extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            color : true,
            sensID : this.props.sensID != null ? this.props.sensID : 1,
            loaded : false
        }
        this.handleClick = this.handleClick.bind(this);
        this.updateDB = this.updateDB.bind(this);
        this.changeState = this.changeState.bind(this);
    }   

    componentDidMount(){ //Checks state of sensor and release button of loading state
        fetch('/api/Requests/jobs')
        .then( (res) => res.json() )
        .then(
            (res) => {
                for (let i = 0; i < res.length; i++) {
                    if(res[i]['SensorID'] == this.state.sensID){
                        console.log(`${res[i]['Action']} || ${this.props.sensID}`);
                        this.setState((prevState) => {
                            this.state.color = res[i]['Action'];
                            this.state.loaded = true;
                        })
                    }
                }
                this.forceUpdate();
            }
        )
    }

    handleClick(){
        if(this.state.loaded){
            this.updateDB();
        }
    }
    
    changeState() {
    }

    updateDB(){
        fetch(`/api/Update/${this.props.apiName != null ? this.props.apiName : 'jobs'}/${this.state.sensID}/${!this.state.color == true ? '1' : '0'}`)
        .then( (res) => {
            this.setState(prevState => {
                this.state.color = !prevState.color;
            });
            this.forceUpdate();
        })
        .catch(
            (err) => {
                console.warn(err)
            }
        )
    }

    render(){
        // console.log('[Debug] Changing Button State  :  '+this.state.color);
        if(this.state.loaded){
            return(
                <button onClick={this.handleClick} className={this.state.color ? styles.ButtonGreen : styles.ButtonRed}>
                    {this.props.children}
                </button>
            );
        } else {
            return(
                <button onClick={this.handleClick} className={styles.ButtonLoad}>
                    Loading...
                </button>
            );
        }
    }
}