import Head from 'next/head'
import Header from '../Components/Header'
import Intro from '../Components/Intro'

export default function Home() {
  return (
    <div className="container">
      <Head>
        <title>Create Next App</title>
        <link rel="icon" href="/favicon.ico" />
        <link rel="stylesheet" type="text/css" href="main.css " />
        <script src='scripts.js' />
      </Head>
      <Header />
      <div className='contents'>
        <Intro />
      </div>
    </div>
  )
}
