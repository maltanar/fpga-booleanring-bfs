package BFSFrontEnd
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    val width = 1
    val depth = 65536

    //chiselMain(args, () => Module(new FrontendController(4096)))
    //chiselMain(args, () => Module(new LevelGenerator(32)))
    chiselMainTest(args, () => Module(new LevelGeneratorTestBed())) { c => new LevelGeneratorTester(c) }
    //chiselMain(args, () => Module(new StreamDeltaGen(32)))
    //chiselMainTest(args, () => Module(new StreamDeltaGenTestBed())) { c => new StreamDeltaGenTester(c) }
    //chiselMain(args, () => Module(new DualPortRAM(width, depth)))
  }
}
