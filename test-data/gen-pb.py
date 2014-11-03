# coding=utf-8
# Générateur de problèmes

import random

class Probleme:

    def __init__(self,src):
        if src == None:
            self.nb_enseignants = 0
            self.nb_cours = 0
            self.nb_creneaux = 0
            self.nb_salles = 0
        else:
            self.nb_enseignants = int(src.ens)
            self.nb_cours = int(src.cours)
            self.nb_creneaux = int(src.creneaux)
            self.nb_salles = int(src.salles)

    def ecrit_nums(self,out):
        out.write("enseignants: {0}\n".format(self.nb_enseignants))
        out.write("salles: {0}\n".format(self.nb_salles))
        out.write("creneaux: {0}\n".format(self.nb_creneaux))
        out.write("cours: {0}\n".format(self.nb_cours))

def gen_rd(nb_src,nb_dest,avgnbdelta,fmt,out):
    l =  map(int,avgnbdelta.split("+"))
    avgnb = l[0]
    if len(l) > 1:
        delta = l[1]
    else:
        delta = 0
    for src in range(0,nb_src):
        taille = max(0,random.randrange(avgnb-delta,avgnb+delta+1))
        if taille > 0:
            lst = range(0,nb_dest)
            random.shuffle(lst)
            lst = lst[:taille]
            lst = ",".join(map(str,lst))
            out.write(fmt.format(src,lst))
        
def gen_enseigne_rd(pb,avgcdelta,out):
    gen_rd(pb.nb_enseignants, pb.nb_cours, avgcdelta,
           "{0} enseigne: {1}\n", out)

def gen_salles(pb,avgsdelta,out):
    gen_rd(pb.nb_cours, pb.nb_salles, avgsdelta,
           "salle pour {0}: {1}\n", out)
    
def gen_indisponibilites(pb,avgcdelta,out):
    gen_rd(pb.nb_enseignants, pb.nb_creneaux, avgcdelta,
           "{0} indisponible: {1}\n", out)

if __name__ == "__main__":
    import argparse
    import sys
    parser = argparse.ArgumentParser()
    parser.add_argument("cours", help="Nombre de cours à placer")
    parser.add_argument("ens", help="Nombre d'enseignants")
    parser.add_argument("salles", help="Nombre de salles")
    parser.add_argument("creneaux", help="Nombre de créneaux")
    parser.add_argument("enseigne", help="n+d signifie que chaque enseignant peut enseigner n plus ou moins d cours")
    parser.add_argument("salle", help="n+d signifie que chaque cours peut être fait dans n plus ou moins d salles")
    parser.add_argument("indisponibilites", help="n+d signifie que chaque enseignant est indisponible durant n plus ou moins d crenaux")
    args = parser.parse_args()
    pb = Probleme(args)
    pb.ecrit_nums(sys.stdout)
    gen_enseigne_rd(pb,args.enseigne,sys.stdout)
    gen_salles(pb,args.salle,sys.stdout)
    gen_indisponibilites(pb,args.indisponibilites,sys.stdout)
