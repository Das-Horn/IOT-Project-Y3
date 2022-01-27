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
        console.log('[Debug] Changing Button State  :  '+this.state.color)
        this.setState(prevState => {
            this.color = !prevState.color
        });
    }

    render(){
        const gC = '#65ff54';
        const rC = '#f75252';
        const gCd = '#3b9131';
        const rCd = '#913131';

        let color
        let colorDark

        if(this.state.color == true){
            color = gC;
            colorDark = gCd;
        } else {            
            color = rC;
            colorDark = rCd;
        }

        const BtnStyle = {
            'background-color' : color,
            'box-shadow' : 5 + 'px ' + 5 + 'px ' + colorDark
        }
        return(
            <button onClick={this.handleClick} className={styles.Button} style={BtnStyle}>
                {this.props.children}
            </button>
        );
    }
}