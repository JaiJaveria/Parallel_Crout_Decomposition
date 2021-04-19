body="\t\t\t{\n    \t\t\t\tsum = 0;\n    \t\t\t\tfor (k = 0; k < j; k++) {\n  \t\t\t\t   sum = sum + L[i][k] * U[k][j];\n \t\t\t\t   }\n \t\t\t\t   L[i][j] = A[i][j] - sum;\n\t\t\t}"
body2="\t\t\t {\n \t\t\t\t U[i][i] = 1;\n \t\t\t }"
print("switch(num_threads){")
for i in {1,2,4,8,16}:
    print("case "+str(i)+":\n{")
    print("\t#pragma omp parallel sections\n \t{")
    #for body
    # inc="(n-j)/"+str(i)
    inc="(n)/"+str(i)
    for j in range(0,i):
        print("\t\t#pragma omp section\n\t\t{")
        #for body
        # print("\t\t\tfor (i=j+"+(str(j)+"*"+inc)+"; i<j+"+(str(j+1)+"*"+inc)+"; i++)")
        #for body2
        print("\t\t\tfor (i="+(str(j)+"*"+inc)+"; i<"+(str(j+1)+"*"+inc)+"; i++)")
        print(body2)
        print("\t\t}")
    print("\t}")
    print("\tbreak;\t\n}")
print("}")
