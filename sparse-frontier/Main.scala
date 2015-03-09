package BFSSparseFrontier

import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {

    //chiselMain(args, () => Module(new NeighborFetcher()))
    chiselMain(args, () => Module(new FrontierFilter()))
    // chiselMainTest(args, () => Module(new NeighborFetcher())) { c => new NeighborFetcherTester(c) }
  }
}
