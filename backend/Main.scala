package BFSBackend
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    //chiselMain(args, () => Module(new RequestGenerator()))
    chiselMainTest(args, () => Module(new RequestGenerator())) { c => new RequestGeneratorTests(c)}
  }
}

