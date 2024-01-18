import numpy as mat

from skfuzzy import control as ctrl
yaya_sayisi=ctrl.Antecedent(mat.arange(0,31,1),"yaya sayısı")
bekleme_suresi= ctrl.Consequent(mat.arange(0,61,1),"geçiş zamanı")
yaya_sayisi.automf(3)
bekleme_suresi.automf(3)

kural1=ctrl.Rule(yaya_sayisi["poor"],bekleme_suresi["poor"])
kural2=ctrl.Rule(yaya_sayisi["average"],bekleme_suresi["average"])
kural3=ctrl.Rule(yaya_sayisi["good"],bekleme_suresi["good"])

kontrol_sure=ctrl.ControlSystem([kural1,kural2,kural3])
sure=ctrl.ControlSystemSimulation(kontrol_sure)
sure.input["yaya sayısı"]=15
sure.compute()
print(sure.output["geçiş zamanı"])
bekleme_suresi.view(sim=sure)
while True:
    continue
