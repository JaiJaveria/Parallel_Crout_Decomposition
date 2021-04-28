import os
import sys
cmd="python3 create_mat.py "+sys.argv[1]+ " > random_mat.txt"
x=os.system(cmd)
for j in [0,1,2,3]:
    for i in [1,2,4,8,16]:
      cmd="time ./a.out "+sys.argv[1]+" random_mat.txt"+" "+str(i)+" "+str(j)
      print(cmd)
      x=os.system(cmd)
      cmd2="diff output_L_0_1.txt output_L_"+str(j)+"_"+str(i)+".txt"
      os.system(cmd2)
      print("")
      cmd3="diff output_U_0_1.txt output_U_"+str(j)+"_"+str(i)+".txt"
      os.system(cmd3)
      if j==0:
          break
      os.system("rm output_L_"+str(j)+"_"+str(i)+".txt")
      os.system("rm output_U_"+str(j)+"_"+str(i)+".txt")
