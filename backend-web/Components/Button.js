import React from "react";
import styles from "../SCSS/Button.module.scss";

export default class Button extends React.Component{
    constructor(props){
        super(props);
        this.state = {
            color : true
        }
        this.handleClick = this.handleClick.bind(this);
    }   

    handleClick(){
        this.setState(prevState => {
            this.state.color = !prevState.color
        });
        this.forceUpdate();
    }
    
    render(){
        // console.log('[Debug] Changing Button State  :  '+this.state.color);
        return(
            <button onClick={this.handleClick} className={this.state.color ? styles.ButtonGreen : styles.ButtonRed}>
                {this.props.children}
            </button>
        );
    }
}