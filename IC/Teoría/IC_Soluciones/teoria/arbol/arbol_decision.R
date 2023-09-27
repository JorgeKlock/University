#!/usr/bin/Rscript
library("rpart")

studentData <- read.csv("datosAlumnos.csv", header=TRUE)

# crea árbol
fit <- rpart(Rama ~ Gusta_mat + Trabajar + Nota + Gusta_hardw + Es_trabajador + Gusta_prog, method="class", data=studentData, minsplit=4)

# exporta árbol
post(fit, file = "./tree.ps",
   title = "Árbol de Clasificación")
