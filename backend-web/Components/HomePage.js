import React from "react";
import styles from "../SCSS/HomePage.module.scss";


export default class HomePage extends React.Component {
    constructor(props){
        super(props);
        this.state = {
            Loading : true
        }
    }

    async componentDidMount(){
        const UName = window.sessionStorage.getItem('UName');
        const Pass = window.sessionStorage.getItem('Pass');

        const Lgin = await fetch(`/api/Login/${UName}/${Pass}`).then(
            (res) => res.json()
        );
        console.log(Lgin);
        if(Lgin.login){
            // this.setState({
            //     Loading : false
            // })
        }else{
            window.location.replace('/');
        }
    }

    render() {
        if(this.state.Loading){
            return(
                <div className={styles.Loading}><div className={styles.ripple}><div></div><div></div>Loading...</div></div>
            );
        }else{
            return(
                <div>Testing Login works</div>
            );
        }
    }
}