import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor

from .. import espaxa_ns, EspAxa

EspAxaStatusSensor = espaxa_ns.class_("EspAxaStatusSensor", sensor.Sensor)
CONF_ESPAXA_ID = "espaxa_id"

CONFIG_SCHEMA = sensor.SENSOR_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(EspAxaStatusSensor),
        cv.GenerateID(CONF_ESPAXA_ID): cv.use_id(EspAxa),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ESPAXA_ID])
    var = cg.new_Pvariable(config["id"])
    await sensor.register_sensor(var, config)
    # cg.add(var.set_parent(parent)) if you implement set_parent
