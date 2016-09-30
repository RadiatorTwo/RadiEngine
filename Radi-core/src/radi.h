#pragma once

//
// Sparky Engine header file
//

#include <radi/app/Application.h>
#include <radi/app/Window.h>

#include <radi/audio/Sound.h>
#include <radi/audio/sound_manager.h>

#include <radi/rddebug/debug_layer.h>
#include <radi/rddebug/debug_menu.h>
#include <radi/rddebug/debug_menu_action.h>
#include <radi/rddebug/debug_menu_item.h>

#include <radi/entity/Entity.h>
#include <radi/entity/component/Component.h>
#include <radi/entity/component/mesh_component.h>
#include <radi/entity/component/transform_component.h>

#include <radi/events/Event.h>
#include <radi/events/key_event.h>
#include <radi/events/mouse_event.h>

#include <radi/graphics/Renderer.h>
#include <radi/graphics/Renderer2D.h>
#include <radi/graphics/Batchrenderer2D.h>
#include <radi/graphics/Renderer3D.h>
#include <radi/graphics/forward_renderer.h>
#include <radi/graphics/deferred_renderer.h>

#include <radi/graphics/Font.h>
#include <radi/graphics/font_manager.h>
#include <radi/graphics/GBuffer.h>
#include <radi/graphics/IRenderable.h>
#include <radi/graphics/Label.h>
#include <radi/graphics/Mask.h>
#include <radi/graphics/Material.h>
#include <radi/graphics/PBRMaterial.h>
#include <radi/graphics/Mesh.h>
#include <radi/graphics/mesh_factory.h>
#include <radi/graphics/Model.h>
#include <radi/graphics/Renderable2D.h>
#include <radi/graphics/render_command.h>
#include <radi/graphics/Scene.h>
#include <radi/graphics/Sprite.h>
#include <radi/graphics/texture_manager.h>

#include <radi/graphics/camera/Camera.h>
#include <radi/graphics/camera/maya_camera.h>
#include <radi/graphics/camera/fps_camera.h>

#include <radi/graphics/layers/Group.h>
#include <radi/graphics/layers/Layer.h>
#include <radi/graphics/layers/Layer2D.h>
#include <radi/graphics/layers/Layer3D.h>

#include <radi/graphics/postfx/post_effects.h>
#include <radi/graphics/postfx/post_effect_pass.h>

#include <radi/graphics/shaders/Shader.h>
#include <radi/graphics/shaders/shader_factory.h>
#include <radi/graphics/shaders/shader_manager.h>
#include <radi/graphics/shaders/shader_uniform.h>

#include <radi/graphics/API/Texture.h>
#include <radi/graphics/API/Texture2D.h>
#include <radi/graphics/API/TextureCube.h>
#include <radi/graphics/API/TextureDepth.h>
#include <radi/graphics/API/Framebuffer.h>
#include <radi/graphics/API/Framebuffer2D.h>
#include <radi/graphics/API/FramebufferDepth.h>

#include <radi/maths/AABB.h>
#include <radi/maths/mat4.h>
#include <radi/maths/maths_func.h>
#include <radi/maths/Quaternion.h>
#include <radi/maths/tvec2.h>
#include <radi/maths/vec2.h>
#include <radi/maths/vec3.h>
#include <radi/maths/vec4.h>

#include <radi/utils/image_load.h>
#include <radi/utils/Log.h>
#include <radi/utils/Timer.h>

#include <radi/system/FileSystem.h>
#include <radi/system/Memory.h>
#include <radi/system/memory_manager.h>
#include <radi/system/VFS.h>

#include <radi/radi_string.h>
#include <radi/radi_types.h>
