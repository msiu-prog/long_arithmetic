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
      @process.print cmd
    end
  end

  def sendnum(num)
    unless @process.nil?
      sendcmd SPLITCMD
      # do something for send number to process 
      sendcmd SPLITCMD  
    end
  end

  def recievenum
    @num = nil
    unless @process.nil?
      sendcmd TOPCMD
      # do something for recieve number from process
      sendcmd SPLITCMD
    end
    @num
  end

  def setup
    @process = IO.popen("#{PROGNAME}", "r+")
    @num = nil
  end

  def teardown
    sendcmd EXITCMD
  end

  def test_start_exit
    sendcmd EXITCMD
    @process.readlines
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

end

