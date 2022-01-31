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
    }   

    handleClick(){
        if(this.state.loaded){
            this.updateDB();
            this.setState(prevState => {
                this.state.color = !prevState.color
            });
            this.forceUpdate();
        }
    }
    
    updateDB(){
        fetch('/api/Request/jobs').then(
            (res) => res.json()
        ).then( (res) => {
            
        })
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