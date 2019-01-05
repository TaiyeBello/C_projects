#!/usr/bin/python
import subprocess
import hashlib;
import sys;

def md5(fname):
    hash_md5 = hashlib.md5()
    with open(fname, "rb") as f:
        for chunk in iter(lambda: f.read(4096), b""):
            hash_md5.update(chunk)
    return hash_md5.hexdigest()

def assertProgramCorrect(program, outFile):
    correct_md5sum = "18ad5255097273b129fd166679fc4e77"
    expectOutput = "0.312000"
    output = runProgram(program)
    md5sum = md5(outFile)
    correct = 1
    if (correct_md5sum != md5sum):
        print "%s is incorrect!" %(outFile)
        correct = 0
    if (output != expectOutput):
        print "Printed output %s is incorrect!"
        correct = 0
    return correct

def runProgram(program):
    p = subprocess.Popen("./"+program, shell=True, stdout=subprocess.PIPE)
    stdout_data = p.communicate()[0]
    output = stdout_data.split()[0]
    return output

# execute main only if called as a script
if __name__ == "__main__":
    if (assertProgramCorrect(sys.argv[1], "output.txt")):
        print "Correct"
