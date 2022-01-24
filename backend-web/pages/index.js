import Head from 'next/head'
import Header from './Components/Header'

export default function Home() {
  return (
    <div className="container">
      <Head>
        <title>Create Next App</title>
        <link rel="icon" href="/favicon.ico" />
        <link rel="stylesheet" type="text/css" href="main.css " />
      </Head>
      <Header ></Header>
    </div>
  )
}
