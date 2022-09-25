PRU Location
/sys/class/remoteproc/remoteprocN

start PRU
echo start > /sys/class/remoteproc/remoteprocN/state

stop PRU
echo stop > /sys/class/remoteproc/remoteprocN/state

load compiled program:
cp dist_lib/*.out /lib/firmware/program_name
echo program_name > /sys/class/remoteproc/remoteprocN/firmware


Set Pin Direction
config-pin {pin} {dir}