#This program receives the data from the file that contains the distance matrix 
#of the proposed method and the p-distance and creates the dendrograms

# Load the necessary libraries
library(tidyverse)
library(dendextend)


dadosHDist <- read.table(file.choose(),header=T,sep=";",dec = ",")
dadosMEGADistp <- read.table(file.choose(),header=T,sep=";",dec = ",")

LysozymeHDist <- as.dist(dadosHDist)
LysozymeMEGADistp <- as.dist(dadosMEGADistp)

# Analyze the cophenetic coefficient
hc <- hclust(LysozymeHDist, "ave") # highest coefficient value 0.9411524 (full beta globine)
d2 <- cophenetic(hc)
cor(LysozymeHDist, d2)
#LysozymeHDist, "ave":      0.9411524 <===
#LysozymeHDist, "ward.D":   0.5728169
#LysozymeHDist, "ward.D2":  0.7822386
#LysozymeHDist, "complete": 0.9226298
#LysozymeHDist, "single":   0.871098
#LysozymeHDist, "mcquitty":  0.9369687
#LysozymeHDist, "median":    0.882386
#LysozymeHDist, "centroid": 0.8976562

hc <- hclust(LysozymeMEGADistp, "ave")  # highest coefficient value 0.9844557
d2 <- cophenetic(hc)
cor(LysozymeMEGADistp, d2)
#LysozymeHDist, "ave":      0.9844557 <===
#LysozymeHDist, "ward.D":   0.7097427
#LysozymeHDist, "ward.D2":  0.7770687
#LysozymeHDist, "complete": 0.9783021
#LysozymeHDist, "single":   0.9774048
#LysozymeHDist, "mcquitty":  0.9805775
#LysozymeHDist, "median":    0.9115328
#LysozymeHDist, "centroid":  0.9607362




# Create two dendrograms, each using a grouping method
# Agglomeration methods:"ward.D", "ward.D2", "single", "complete", 
#                         "average" (= UPGMA), "mcquitty" (= WPGMA), 
#                         "median" (= WPGMC) or "centroid" (= UPGMC).

dend1 <- LysozymeHDist %>% hclust( method="ave" ) %>% as.dendrogram()
dend2 <- LysozymeMEGADistp %>% hclust( method="ave" ) %>% as.dendrogram()
# coefficient 0.8789737
cor_cophenetic(dend1, dend2, method_coef = "kendall")

#dend1 <- ladderize(dend1)#This function rearranges the internal structure of the tree to get the stair effect when plotted.
#dend2 <- ladderize(dend2)


# Color according to the k big groups
dendlista <- dendlist(
  dend1 %>% 
    set("labels_col", value =c(1:7), k=7) %>%
    set("branches_lty", 1) %>%
    set("branches_k_color", value =c(1:7), k=7) %>%
    set("labels_cex",1.5),
  dend2 %>% 
    set("labels_col", value =c(1:7), k=7) %>%
    set("branches_lty", 1) %>%
    set("branches_k_color", value = c(1:7), k=7) %>%
    set("labels_cex", 1.5)
)




# Plot the dendrograms side by side
tanglegram(dendlista, 
           common_subtrees_color_lines = FALSE, highlight_distinct_edges  = TRUE, highlight_branches_lwd=FALSE,
           margin_inner=15,
           lwd=2,
           main_left = "(A)",
           main_right = "(B)"
)

dev.copy(pdf, 'Dendograma.pdf', width = 10, height = 10)
dev.off()

