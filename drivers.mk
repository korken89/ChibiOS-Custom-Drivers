# Drivers directory location from Makefile
DRIVERS_DIR = ./drivers

# Imported source files and paths from drivers
include $(DRIVERS_DIR)/eicu/eicu.mk
include $(DRIVERS_DIR)/epwm/epwm.mk

# List of all the related files.
ADRIVERSSRC = $(EICUSRC) $(EPWMSRC)

# Required include directories
ADRIVERSINC = $(EICUINC) $(EPWMINC)
