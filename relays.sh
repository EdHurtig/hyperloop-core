# Step 1:
for i in {86,88,87,89,10,11,9,81,8,80,78,79,76,77,74,75,72,73,70,71}; do
  test -d /sys/class/gpio/gpio$i/ || echo $i > /sys/class/gpio/export
done

# Step 2: Check if any exports failed
for i in {86,88,87,89,10,11,9,81,8,80,78,79,76,77,74,75,72,73,70,71}; do
  test -d /sys/class/gpio/gpio$i/ || { echo Missing gpio$i; exit 1 }
done

while [ true ]; do
# Step 3: Set direction to output
for i in {86,88,87,89,10,11,9,81,8,80,78,79,76,77,74,75,72,73,70,71}; do
  echo out > /sys/class/gpio/gpio$i/direction
done

for i in {86,88,87,89,10,11,9,81,8,80,78,79,76,77,74,75,72,73,70,71}; do
  echo 1 > /sys/class/gpio/gpio$i/value
done

sleep 1

# Step 4: Set all LCD GPIOs HIGH
for i in {86,88,87,89,10,11,9,81,8,80,78,79,76,77,74,75,72,73,70,71}; do
  echo 0 > /sys/class/gpio/gpio$i/value
done

sleep 1
done
