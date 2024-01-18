import numpy as n
import  skfuzzy as f
from skfuzzy import control as c

homework = c.Antecedent(n.arange(0,21,1),"homework")
study_time=c.Consequent(n.arange(0,600,1),"study_time")
homework["low"]=f.trimf(homework.universe,[1,3,6])
homework["mid"]=f.trimf(homework.universe,[4,9,14])
homework["high"]=f.trimf(homework.universe,[10,15,20])

study_time["low"]=f.trimf(study_time.universe,[30,60,180])
study_time["mid"]=f.trimf(study_time.universe,[120,300,420])
study_time["high"]=f.trimf(study_time.universe,[300,450,600])

rule1= c.Rule(homework["low"],study_time["low"])
rule2= c.Rule(homework["mid"],study_time["mid"])
rule3= c.Rule(homework["high"],study_time["high"])
timeControl=c.ControlSystem([rule1,rule2,rule3])
time=c.ControlSystemSimulation(timeControl)

while True:
    time.input["homework"]=int(input("Ödev sayını gir: "))
    time.compute()
    print(f"{str(time.output['study_time']/60)[:3]} saat")
