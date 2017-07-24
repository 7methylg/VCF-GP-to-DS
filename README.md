# VCF-GP-to-DS
Script to convert the GP column of a VCF to VCF of minor allele dosage, then annotate original file with the dosage. Assumes column INFO/AF (alternate allele frequency). Requires bcftools (v1.3.1 or above), bgzip, and tabix executables in bin.

To compile: gcc -O3 -o convert dosage_convert.c

To run: ./convert_dosage.sh path_to_vcf.vcf.gz

Creates dosage-${original_file.vcf.gz} as vcf file of only dosage, and dosage.${original_file.vcf.gz} as annotated original file.

Feel free to leave questions in issues, it is a pretty simple script.

Big thanks to the Engert-Thanassoulis Lab at the MUHC for their support!
