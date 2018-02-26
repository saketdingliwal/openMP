import os
import subprocess
import math

core_count = 1
for j in range(5):
	summ = 0.0
	for k in range(20):
		prog = "./a.out"
		core_str = str(core_count)
		inp_str = " < seahorse.ascii.pbm"
		arg = [core_str,inp_str]
		command = [prog]
		command.extend(arg)     
		proc = subprocess.Popen(command, stdout=subprocess.PIPE)
		summ += (float)(proc.stdout.read())
		print summ
	print core_count,";",(summ/20),";",math.log(summ/20)
	core_count = core_count * 2