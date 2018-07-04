#!/usr/bin/env python
# This is for checking if 1_6 is right
# Date: 2015.3.15
# Made by linamy85

import random, subprocess, os
times = int(input(">>> times = "))

def gcd(a, b):
	m = min(a, b)
	n = max(a, b)
	
	while (n % m != 0):
		tmp = m
		m = n % m
		n = tmp
	return m

flag = 0

for a in range(1, times):
	a = random.randrange(10**0, 10**256)
	b = random.randrange(10**0, 10**256)
	g = random.randrange(10**0, 10**4)
	a *= g
	b *= g

	result = gcd(a, b)
	cmd = 'echo '+str(a)+' '+str(b)+' | ./gcd_by_binary'
	#print cmd
	proc = os.popen(cmd)
	#proc = subprocess.Popen(cmd, stdout=subprocess.PIPE)
	answer = int(proc.read())
	string = "gcd(\n  %d,\n  %d\n) = %d" %(a, b, result)
	print string	
	if (answer != result):
		flag = 1
		break;

if flag == 0:
	print "True"
else:
	print "False"

