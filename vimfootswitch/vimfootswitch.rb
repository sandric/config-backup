#!/usr/bin/ruby

# Must install libusb library via your favorite package manager
# Then install libusb ruby gem, via $ sudo gem install libusb
require './libusb'


# Call provided blocks when key is pressed or released
def handle_pedal(device, onpress, onrelease)
  device.open do |h|     

    # Since any decent OS will automatically supply an USB
    # keyboard driver, disable it if necessary.
    h.detach_kernel_driver(0) if h.kernel_driver_active?(0)

    begin
      # Seize control of the device
      h.claim_interface(0) do |ign|        
        pressed = false
        endpoint = device.interfaces[0].endpoints[0]

        loop do
          # Grab N key's at a time
          keys = h.interrupt_transfer(:endpoint=>endpoint, :dataIn=>endpoint.wMaxPacketSize(), :timeout=>0).unpack("Q*")
          h.clear_halt(endpoint)

          # Manage state and transitions
          if pressed
            pressed = false if keys.select { |x| x > 1 }.length < keys.length
            onrelease.call if onrelease and !pressed
              
          else
            pressed = true if keys.select { |x| x > 1 }.length > 0 
            onpress.call if pressed and onpress
          end
        end
      end
    rescue => e
      $stderr.puts "An exception occured! #{e.message} -> #{e.backtrace}"
    ensure
      # Make sure we *ALWAYS* release device control back to the OS
      h.attach_kernel_driver(0) unless h.kernel_driver_active?(0)
    end
  end
end


# Initialize
usb = LIBUSB::Context.new

# Find first USB Pedal
device_first = usb.devices(:idVendor => 0x0c45, :idProduct => 0x7403).first


# Define your own press/release behavior here
#onpress   = Proc.new { puts "Pressed"  }
#onrelease = Proc.new { puts "Released" }

# Vim Clutch in software for X,
# from: https://github.com/alevchuk/vim-clutch
# Requires "xautomation", $ sudo apt-get install xautomation
onpress   = Proc.new do 
  raise "xte failed to hit key" unless system("xte 'key Escape'")
end  
onrelease = Proc.new do 
  raise "xte failed to hit key" unless system("xte 'key i'")
end  

# Run Forrest Run!
handle_pedal(device_first, onpress, onrelease)
