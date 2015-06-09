package BFSSparseFrontier

import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    val resultMemDepthWords = 1024 * 28
    //chiselMain(args, () => Module(new NeighborFetcher()))
    //chiselMain(args, () => Module(new FrontierFilter()))
    chiselMain(args, () => Module(new SparseFrontierBackend()))
    //chiselMain(args, () => Module(new LevelGenerator(64)))
    //chiselMain(args, () => Module(new SparseFrontierFrontend(resultMemDepthWords)))
    //chiselMain(args, () => Module(new DistVecToInpVec(64)))
    //chiselMain(args, () => Module(new AXIStreamInputMux(32)))
    //chiselMain(args, () => Module(new BackendThrottler()))
  }
}
