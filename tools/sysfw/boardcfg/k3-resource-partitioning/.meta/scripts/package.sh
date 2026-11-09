SCRIPT=$(readlink -f $0)
SCRIPTPATH=`dirname $SCRIPT`
SCRIPTPATH=`dirname $SCRIPTPATH`
SCRIPTPATH=`dirname $SCRIPTPATH`
version=`jq -r '.version' $SCRIPTPATH/.metadata/product.json | sed 's/\./_/g'`
packagedir=k3_respart_tool_$version
zipname=K3_Resource_Config_$version

cd $SCRIPTPATH/
rm -rf $packagedir
mkdir $packagedir
mkdir -p $packagedir/.meta/modules
mkdir -p $packagedir/.meta/data
mkdir $packagedir/out

# Create a file to describe the baseline for package
commit=`git log -1 --pretty=format:"%H"`
echo "Package created on `date`" >> $packagedir/manifest.txt
echo "Baseline commit SHA-1 - $commit" >> $packagedir/manifest.txt

# Copy the static data
cp .meta/modules/*.js $packagedir/.meta/modules/
cp .meta/data/tifsResRem.json $packagedir/.meta/data/
cp -r .metadata $packagedir/
cp -r .meta/scripts .meta/templates $packagedir/.meta/
rm -rf $packagedir/.meta/scripts/node_modules
rm $packagedir/.meta/scripts/package.sh $packagedir/.meta/scripts/generate-data.sh $packagedir/.meta/scripts/generate-json.py $packagedir/.meta/scripts/sysconfig-deviceData-update.sh

if [ $# -eq 0 ]; then
	# Copy all the files for all SoC when no SoC is specified
	echo "Generating package for all SoC"
	cp -r out/ $packagedir/
	cp -r .meta/data/ $packagedir/.meta/
	cp -r .meta/modules/*/ $packagedir/.meta/modules/
	if [ -d ".meta/deviceData" ]; then
		mkdir -p $packagedir/.meta/deviceData
		cp -r .meta/deviceData $packagedir/.meta/
	fi
else 
	# Create baseline JSON files
	echo "Generating package"
	echo "[]" > $packagedir/.meta/data/SOC.json
	jq '.devices = []' .metadata/product.json > $packagedir/.metadata/product.json
	jq '.[].tags = ["K3-RESOURCE-CONFIGURATION","Resource Configuration","Respart", "K3-Respart-Tool", "Resource Partitioning", "QoS", "Firewall", "Resource Sharing"]' .metadata/.tirex/package.tirex.json | jq '.[].devices = []' > $packagedir/.metadata/.tirex/package.tirex.json
fi

while [ $# -gt 0 ]
do
	soc=$1

	# Copy the soc specific data
	cp -r .meta/modules/$soc $packagedir/.meta/modules/
	cp -r .meta/data/$soc $packagedir/.meta/data/
	cp out/*$soc* $packagedir/out/
	if [ -d ".meta/deviceData/$soc" ]; then
		mkdir -p $packagedir/.meta/deviceData
		cp -r .meta/deviceData/$soc $packagedir/.meta/deviceData/
	fi

	# Update baseline JSON files with all device names for a SoC
	dev_names=`jq -r '.[] | select(.shortName == "'$soc'") | .soc' .meta/data/SOC.json`
	for device in $dev_names;
	do
		echo "Adding $soc - $device"
		jq -s --tab --sort-keys '(.[0] + [.[1][] | select(.soc == "'$device'")])' \
			$packagedir/.meta/data/SOC.json .meta/data/SOC.json > temp
		mv temp $packagedir/.meta/data/SOC.json

		jq --tab --sort-keys '.devices = .devices + ["'$device'"]' \
			$packagedir/.metadata/product.json > temp
		mv temp $packagedir/.metadata/product.json

		jq --tab --sort-keys '.[].tags = .[].tags + ["'$device'"]' \
			$packagedir/.metadata/.tirex/package.tirex.json | \
		jq --tab --sort-keys '.[].devices = .[].devices + ["'$device'"]' > temp
		mv temp $packagedir/.metadata/.tirex/package.tirex.json
	done
	shift
done

jq --tab --sort-keys 'sort_by(.soc)' \
	$packagedir/.meta/data/SOC.json > temp
mv temp $packagedir/.meta/data/SOC.json

# Create final package
zip -qq -r $zipname\_all.zip $packagedir
echo "Generated package: ${zipname}_all.zip"

# Update the handoff json
sed -i 's/K3_Resource_Config_[0-9]\+_[0-9]\+_[0-9]\+/'$zipname'/g' handoff.json
echo "Updated handoff.json for handing off to TIREX"
echo "Done"
