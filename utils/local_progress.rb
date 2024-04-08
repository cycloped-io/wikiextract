require 'progress'

class LocalProgress
  # The number of times progress will be reported in quiet mode.
  TICKS = 100
  def initialize(title, total, quiet: false, log: nil)
    @quiet = quiet
    @cumulative_work = 0
    @reported = 0
    @step = total / TICKS
    @step = 1 if @step == 0
    @title = title
    @start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
    if(@quiet)
      unless log.nil?
        @file = File.open(log, "a")
        @file.puts("Started [#{Process.pid}] '#{@title}': #{total}")
      end
    else
      Progress.start(@title, total)
    end
  end

  def step(amount)
    if(@quiet)
      unless(@file.nil?)
        @cumulative_work += amount
        steps = @cumulative_work / @step
        if  steps > @reported
          @file.puts("Processed [#{Process.pid}] #{steps}%")
          @file.flush()
          @reported = steps
        end
      end
    else
      Progress.step(amount)
    end
  end

  def stop(quiet: false)
    end_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
    if(@quiet)
      unless(@file.nil?)
        @file.puts("Finished [#{Process.pid}] '#{@title}' in %.6f" % [end_time - @start_time])
        @file.close
      end
    else
      Progress.stop
    end
  end
end