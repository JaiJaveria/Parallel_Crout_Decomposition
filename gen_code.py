import sys

body0="\t\t\t{\n    \t\t\t\tsum = 0;\n    \t\t\t\tfor (k = 0; k < j; k++) {\n  \t\t\t\t   sum = sum + L[i][k] * U[k][j];\n \t\t\t\t   }\n \t\t\t\t   L[i][j] = A[i][j] - sum;\n\t\t\t}"
body1="\t\t\t {\n \t\t\t\t U[i][i] = 1;\n \t\t\t }"
body2="\t\t\t{\n \t\t\t\tsum = 0;\n\t\t\t\tfor(k = 0; k < j; k++) {\n\t\t\t\tsum = sum + L[j][k] * U[k][i];\n\t\t\t\t}\n\t\t\t\tif (L[j][j] == 0) {\n\t\t\t\t// exit(0);\n\t\t\t\treturn;\n\t\t\t\t}\n\t\t\t\tU[j][i] = (A[j][i] - sum) / L[j][j];\n\t\t\t}"

print("switch(num_threads){")
for i in {1,2,4,8,16}:
    print("case "+str(i)+":\n{")
    print("\t#pragma omp parallel sections\n \t{")
    inc=""
    #for body
    if sys.argv[1]=="0" or sys.argv[1]=="2":
        inc="(n-j)/"+str(i)
    elif sys.argv[1]=="1":
        inc="(n)/"+str(i)
    for j in range(0,i):
        print("\t\t#pragma omp section\n\t\t{")
        #for body
        if sys.argv[1]=="0":
            print("\t\t\tfor ( i=j+"+(str(j)+"*"+inc)+"; i<j+"+(str(j+1)+"*"+inc)+"; i++)")
            print(body0)
        elif sys.argv[1]=="1":
        #for body2
            print("\t\t\tfor ( i="+(str(j)+"*"+inc)+"; i<"+(str(j+1)+"*"+inc)+"; i++)")
            print(body1)
        elif sys.argv[1]=="2":
            print("\t\t\tfor ( i=j+"+(str(j)+"*"+inc)+"; i<j+"+(str(j+1)+"*"+inc)+"; i++)")
            print(body2)
        print("\t\t}")
    print("\t}")
    print("\tbreak;\t\n}")
print("}")
