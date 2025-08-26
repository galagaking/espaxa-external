import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import cover

from .. import espaxa_ns, EspAxa

EspAxaCover = espaxa_ns.class_("EspAxaCover", cover.Cover)
CONF_ESPAXA_ID = "espaxa_id"

CONFIG_SCHEMA = cover.COVER_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(EspAxaCover),
        cv.GenerateID(CONF_ESPAXA_ID): cv.use_id(EspAxa),
    }
)

async def to_code(config):
    parent = await cg.get_variable(config[CONF_ESPAXA_ID])
    var = cg.new_Pvariable(config["id"])
    await cover.register_cover(var, config)
    cg.add(var.set_parent(parent))
