#!/usr/bin/ruby

require 'test/unit'


class LongArithmeticsTest < Test::Unit::TestCase

  PROGNAME = "./calc"
  
  # commands
  EXITCMD = "q"

  ADDCMD = "+"
  SUBCMD = "-"
  MULTCMD = "*"
  DIVCMD = "/"

  TOPCMD = "t"
  POPCMD = "p"

  SPLITCMD = " "

  def sendcmd(cmd)
    unless @process.nil?
      @write.print cmd
      @read.gets if cmd == POPCMD
      @write.flush
    end
  end

  def sendnum(num)
    unless @process.nil?
      sendcmd SPLITCMD
      @write.print num.to_s(16).gsub(/-/, '~')
      sendcmd SPLITCMD  
    end
  end

  def recievenum
    @num = nil
    unless @process.nil?
      sendcmd TOPCMD
      @num = @read.gets.to_i(16)
      sendcmd SPLITCMD
    end
    @num
  end

  def setup
    subproc_read, @write = IO.pipe
    @read, subproc_write = IO.pipe
    if (@process = fork)
      subproc_read.close
      subproc_write.close
    else
      @write.close
      @read.close

      $stdin.reopen subproc_read
      $stdout.reopen subproc_write

      exec PROGNAME
      exit 1
    end
    @num = nil
  end

  def teardown
    sendcmd EXITCMD
    Process.waitpid @process
  end

  def test_start_exit
  end
  
  def test_sendnum
    sendnum 2
  end

  def test_recievenum
    sendnum 3
    assert_equal(3, recievenum)
  end

  def test_add_simple
    sendnum 0
    sendnum 0
    sendcmd ADDCMD
    assert_equal(0, recievenum)
   
    sendcmd POPCMD

    sendnum 0
    sendnum 1
    sendcmd ADDCMD
    assert_equal(1, recievenum)

    sendnum 2
    sendnum 3
    sendcmd ADDCMD
    assert_equal(5, recievenum)
   
    sendcmd ADDCMD
    assert_equal(6, recievenum)

    sendcmd POPCMD
  end

  def test_sub_simple
    sendnum 7
    sendnum 3
    sendcmd SUBCMD
    assert_equal(4, recievenum)

    sendcmd POPCMD

    sendnum 9
    sendnum 2
    sendcmd SUBCMD
    assert_equal(7, recievenum)

    sendnum 5
    sendnum 1
    sendcmd SUBCMD
    assert_equal(4, recievenum)
    
    sendcmd SUBCMD
    assert_equal(3, recievenum)

    sendcmd POPCMD
  end

  def test_mult_simple
    sendnum 12
    sendnum 6
    sendcmd MULTCMD
    assert_equal(72, recievenum)

    sendcmd POPCMD
    
    sendnum 3
    sendnum -4
    sendnum 2
    sendcmd MULTCMD
    assert_equal(-8, recievenum)
 
    sendcmd MULTCMD
    assert_equal(-24, recievenum)
  end
  
  def test_mult_special
    a = 93878492347712341634713254403146132987462340238410236412333339
    b = 15970815719482634412340398470932847783247123642364923487621934786192387469234
    
    sendnum a
    sendnum b
    sendcmd MULTCMD
    assert_equal(a*b, recievenum)
    
    #test on wiki number
    a = -2560135624671332861315724674672476481682
    b = 54308428790203478762340052723346983453487023489987231275412390872348475
    #b is the wiki number, see http://ru.wikipedia.org/wiki/%D0%92%D0%B8%D0%BA%D0%B8%D0%BF%D0%B5%D0%B4%D0%B8%D1%8F:54308428790203478762340052723346983453487023489987231275412390872348475 
    
    sendnum a
    sendnum b
    sendcmd MULTCMD
    assert_equal(a*b, recievenum)
    
  end
end

