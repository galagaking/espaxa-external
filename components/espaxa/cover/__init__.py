import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor
from esphome.const import CONF_ID
from .. import espaxa_ns, EspAxa

EspAxaStatusSensor = espaxa_ns.class_("EspAxaStatusSensor", sensor.Sensor)
CONF_ESPAXA_ID = "espaxa_id"

CONFIG_SCHEMA = sensor.sensor_schema(EspAxaStatusSensor).extend(
    {
        cv.GenerateID(CONF_ESPAXA_ID): cv.use_id(EspAxa),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ESPAXA_ID])
    var = cg.new_Pvariable(config[CONF_ID])
    await sensor.register_sensor(var, config)
    # cg.add(var.set_parent(parent))  # if you add set_parent on the C++ side
