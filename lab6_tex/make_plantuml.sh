

for filename in ./plantuml/*.plantuml; do
    echo $filename
    java -jar ../../plantuml-1.2021.16.jar $filename 
done

