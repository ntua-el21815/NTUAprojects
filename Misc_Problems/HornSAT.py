
def eliminate_unit_clauses(clauses, unit_clauses,final_expr):
    for clause in clauses:
        if len(clause) == 1: #Unit clauses must be set to True otherwise horn sat is not possible
            if clause[0] not in unit_clauses:
                unit_clauses.append(clause[0])
                final_expr.append(clause[0])
                clauses.remove(clause)
    done = True #If there are no more unit clauses, we are done
    for unit_clause in unit_clauses:
        for clause in clauses:
            if unit_clause in clause:
                clauses.remove(clause) #If a unit clause is present in a clause then it is always true and can be removed
                done = False 
            elif -unit_clause in clause:
                clause.remove(-unit_clause) #The complement of a unit clause is always false and hence can be removed
                done = False
    if not done:
        eliminate_unit_clauses(clauses, unit_clauses,final_expr)
    else:
        return 

def horn_sat(clauses, unit_clauses,final_expr):
    eliminate_unit_clauses(clauses, unit_clauses,final_expr)
    for clause in clauses:
        if len(clause) == 0:
            return (False,None) #If there is an empty clause,that means that a variable would have to be both true and false which is not possible
    for lit in range (1,v+1):
        if -lit in final_expr and lit in unit_clauses:
            return (False,None) #This means again that a variable must be both true and false which is not possible
    for lit in range(1,v+1):
            if lit not in final_expr and (-lit) not in final_expr:
                final_expr.append(-lit) #Set all literals that are not unit clauses to false
    final_expr.sort(key = abs)
    return (True,final_expr)
    

inputs = input().split()
unit_clauses = []
clauses = []
final_expr = []
''' Σύμβαση
    Input:
    v c
    -1 2 
    1 -2 
    1 2 
    Εδώ v = 2 και c = 3 και για ευκολία θα αντιστοιχίσουμε το 1 στο x1 και το 2 στο x2 το -1 στο not x1 και το -2 στο not x2
    Output: 
    Ναι ή Όχι (Αν είναι ικανοποιήσιμος ο τύπος ή όχι)
    Αν Ναι: Η v-αδα των αληθοτιμών των μεταβλητών
    '''
v = int(inputs[0])
c = int(inputs[1])
for i in range(c):
    clause = input()
    clause = clause.split()
    clause = [int(x) for x in clause]
    clauses.append(clause)
if horn_sat(clauses, unit_clauses,final_expr)[0]:
    print("Ναι")
    print("(" ,end = "")
    for i in range(len(final_expr)-1):
        if final_expr[i] > 0:
            print("True", end = ",")
        else:
            print("False", end = ",")
    if final_expr[len(final_expr)-1] > 0:
            print("True", end = "")
    else:
            print("False", end = "")
    print(")")
else:
    print("Όχι")

'''Ο Αλγόριθμος έχει πολυπλοκότητα Ο(c*v) καθώς len(unit_clauses) <= v και len(clauses) = c
   και επεξεργάζεται κάθε clause len(unit_clauses) φορές''' 



