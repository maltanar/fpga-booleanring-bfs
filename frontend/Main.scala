package BFSFrontEnd
import Chisel._

object MainObj {
  def main(args: Array[String]): Unit = {
    val width = 1
    val depth = 65536
    
    chiselMain(args, () => Module(new DualPortRAM(width, depth)))
  }
}

