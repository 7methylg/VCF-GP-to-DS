# VCF-GP-to-DS
Script to convert the GP column of a VCF to VCF of minor allele dosage, which can be used for analysis or annotation. Assumes column INFO/AF (alternate allele frequency). Requires bcftools executable in bin.

To compile: gcc -O3 -o convert dosage_convert.c

To run: ./convert_dosage.sh ${path to GP file}
