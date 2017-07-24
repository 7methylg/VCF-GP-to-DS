#!/bin/bash

file=$1

lines=`bcftools view -h "$file" | wc -l`
bcftools view -h "$file" | head -$((lines-1)) >> dosage-"$file"
echo "##FORMAT<ID=DS,Number=1,Type=Float,Description=\"Minor allele dosage\">" >> dosage-"$file"
bcftools view -h "$file" | tail -1 >> dosage-"$file"

bcftools query -f '%CHROM\t%POS\t%ID\t%REF\t%ALT\t%QUAL\t%FILTER\n' "$file" > "$file".infos

echo "beginning conversion $file"

head_count=`bcftools view -h "$file" | tail -1 | tr '\t' '\n' | wc -l`
indivs=$((head_count-9))

./convert "$file" indivs

echo "conversion done. zipping dosage-$file..."

bgzip dosage-"$file"
tabix dosage-"$file"
rm "$file".infos

echo "$file zipped and ready to go!"

echo "beginning annotation $file"

bcftools annotate -a dosage-"$file" -c FORMAT/DS "$file" | bgzip -c > dosage."$file"

