#pragma once

//
// Radi Engine header file
//

#include <radi/app/application.h>

#include <radi/audio/sound.h>
#include <radi/audio/sound_manager.h>

#include <radi/entity/entity.h>
#include <radi/entity/component/component.h>
#include <radi/entity/component/mesh_component.h>
#include <radi/entity/component/transform_component.h>

#include <radi/events/event.h>
#include <radi/events/key_event.h>
#include <radi/events/mouse_event.h>

#include <radi/graphics/renderer2d.h>
#include <radi/graphics/batchrenderer2d.h>
#include <radi/graphics/renderer3d.h>
#include <radi/graphics/forward_renderer.h>

#include <radi/graphics/font.h>
#include <radi/graphics/font_manager.h>
#include <radi/graphics/framebuffer.h>
#include <radi/graphics/irenderable.h>
#include <radi/graphics/label.h>
#include <radi/graphics/mask.h>
#include <radi/graphics/material.h>
#include <radi/graphics/mesh.h>
#include <radi/graphics/mesh_factory.h>
#include <radi/graphics/model.h>
#include <radi/graphics/renderable2d.h>
#include <radi/graphics/render_command.h>
#include <radi/graphics/scene.h>
#include <radi/graphics/sprite.h>
#include <radi/graphics/texture.h>
#include <radi/graphics/texture_manager.h>
#include <radi/graphics/window.h>

#include <radi/graphics/buffers/buffer.h>
#include <radi/graphics/buffers/buffer_layout.h>
#include <radi/graphics/buffers/indexbuffer.h>
#include <radi/graphics/buffers/vertexarray.h>

#include <radi/graphics/camera/camera.h>
#include <radi/graphics/camera/maya_camera.h>

#include <radi/graphics/layers/group.h>
#include <radi/graphics/layers/layer.h>
#include <radi/graphics/layers/layer2d.h>
#include <radi/graphics/layers/layer3d.h>

#include <radi/graphics/postfx/post_effects.h>
#include <radi/graphics/postfx/post_effect_pass.h>

#include <radi/graphics/shaders/shader.h>
#include <radi/graphics/shaders/shader_factory.h>
#include <radi/graphics/shaders/shader_uniform.h>

#include <radi/maths/aabb.h>
#include <radi/maths/mat4.h>
#include <radi/maths/maths_func.h>
#include <radi/maths/quaternion.h>
#include <radi/maths/tvec2.h>
#include <radi/maths/vec2.h>
#include <radi/maths/vec3.h>
#include <radi/maths/vec4.h>

#include <radi/utils/fileutils.h>
#include <radi/utils/image_load.h>
#include <radi/utils/log.h>
#include <radi/utils/stringutils.h>
#include <radi/utils/timer.h>

#include <radi/radi_string.h>
#include <radi/radi_types.h>
