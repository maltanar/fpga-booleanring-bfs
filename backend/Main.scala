package BFSBackend
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    //chiselMain(args, () => Module(new RequestGenerator()))
    chiselMain(args, () => Module(new RequestGeneratorWrapper()))
    //chiselMainTest(args, () => Module(new RequestGenerator())) { c => new RequestGeneratorTests(c)}
  }
}
