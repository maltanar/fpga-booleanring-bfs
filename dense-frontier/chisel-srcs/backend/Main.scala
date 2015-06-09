package BFSBackend
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    //chiselMain(args, () => Module(new RequestGenerator()))
    chiselMain(args, () => Module(new RequestGeneratorWrapper()))
    //chiselMain(args, () => Module(new WriteGenerator()))
    //chiselMainTest(args, () => Module(new RequestGenerator())) { c => new RequestGeneratorTests(c)}
    //chiselMainTest(args, () => Module(new AXIStreamDownsizer(64,16))) { c => new AXIStreamDownsizerTester(c)}
  }
}
