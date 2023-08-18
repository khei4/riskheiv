package core
import chisel3.stage.{ChiselStage, ChiselGeneratorAnnotation}


object Main extends App {
    // These lines generate the Verilog output
    // FIXME: FIRRTL randomization is noisy, but following options doesn't work on this FIRRTL version
    // (new chisel3.stage.ChiselStage).execute(
    // Array("-X", "verilog", "-disable-all-randomization", "-strip-debug-info"),
    // Seq(ChiselGeneratorAnnotation(() => new Top)))
    val verilogString = (new chisel3.stage.ChiselStage).emitVerilog(new Top)
    println(verilogString)
}