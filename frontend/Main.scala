package BFSFrontEnd
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    val resultMemDepthWords = 1024 * 28

    //chiselMain(args, () => Module(new FrontendController(resultMemDepthWords)))
    //chiselMain(args, () => Module(new FrontendControllerTurbo(resultMemDepthWords)))
    chiselMain(args, () => Module(new StateProfiler(8)))
    //chiselMain(args, () => Module(new LevelGenerator(32)))
    //chiselMainTest(args, () => Module(new LevelGeneratorTestBed())) { c => new LevelGeneratorTester(c) }
    //chiselMain(args, () => Module(new StreamDeltaGen(32)))
    //chiselMainTest(args, () => Module(new StreamDeltaGenTestBed())) { c => new StreamDeltaGenTester(c) }
    //chiselMain(args, () => Module(new DualPortRAM(width, depth)))
  }
}
