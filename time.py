import os
import subprocess


core_count = 1
for j in range(5):
	n = 2
	for i in range(22):
		summ = 0.0
		for k in range(20):
			prog = "./a.out"
			str_n = str(n)
			core_str = str(core_count)
			arg = [str_n,core_str]
			command = [prog]
			command.extend(arg)     
			proc = subprocess.Popen(command, stdout=subprocess.PIPE)
			summ += (float)(proc.stdout.read())
		print n,";",core_count,";",(summ/20)
		n = n * 2
	core_count = core_count * 2