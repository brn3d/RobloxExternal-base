#pragma once

namespace thenwefuckin::settings
{
    inline bool  box_enabled = false;
    inline float box_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  box_outline = true;
    inline float box_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  box_filled = false;
    inline bool  box_fill_gradient = false;
    inline float box_fill_color[4] = { 0.0f, 0.0f, 0.0f, 0.5f };
    inline float box_fill_color2[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
    inline int   box_mode = 1;
    inline bool  box_dynamic() { return box_mode == 1; }
    inline bool  box_static() { return box_mode == 0; }
    inline int   box_style = 0;
    inline bool  box_corner() { return box_style == 1; }
    inline bool  box_full() { return box_style == 0; }

    inline bool  skeleton_enabled = false;
    inline float skeleton_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  skeleton_outline = true;
    inline float skeleton_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    inline bool  health_enabled = false;
    inline bool  health_outline = true;
    inline float health_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline float health_color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    inline bool  health_gradient = true;
    inline bool  health_text = true;

    inline bool  name_enabled = false;
    inline float name_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  name_outline = true;
    inline float name_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    inline bool  headdot_enabled = false;
    inline float headdot_color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
    inline bool  headdot_fill = true;
    inline bool  headdot_outline = true;
    inline float headdot_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline float headdot_thickness = 3.0f;

    inline bool  distance_enabled = false;
    inline float distance_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  distance_outline = true;
    inline float distance_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    inline bool  tool_enabled = false;
    inline float tool_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  tool_outline = true;
    inline float tool_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  tool_distance_check = false;
    inline float tool_distance_value = 500.0f;

    inline bool  flags_enabled = false;
    inline float flags_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  flags_outline = true;
    inline float flags_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  flags_global = false;
    inline bool  flags_team = true;
    inline float flags_team_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  flags_team_outline = true;
    inline float flags_team_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  flags_state = true;
    inline float flags_state_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  flags_state_outline = true;
    inline float flags_state_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  flags_health = true;
    inline float flags_health_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  flags_health_outline = true;
    inline float flags_health_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

    inline bool  tracer_enabled = false;
    inline float tracer_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  tracer_outline = true;
    inline float tracer_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline int   tracer_origin = 0;
    inline float tracer_thickness = 1.2f;

    inline bool  oof_enabled = false;
    inline float oof_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  oof_outline = true;
    inline float oof_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline float oof_size = 7.0f;
    inline int   oof_arrow_style = 0;
    inline bool  oof_names = false;
    inline float oof_name_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  oof_health = false;
    inline float oof_health_color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    inline bool  oof_distance = false;
    inline float oof_distance_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  oof_avatar = false;
    inline float oof_radius = 30.0f;

    inline bool  aim_enabled = false;
    inline int   aim_key = 0;
    inline int   aim_key_mode = 2;
    inline int   aim_method = 0;
    inline int   aim_part = 0;
    inline float aim_fov = 150.0f;
    inline bool  aim_smoothing_enabled = true;
    inline float aim_smoothing = 5.0f;
    inline float aim_smoothing_x = 5.0f;
    inline float aim_smoothing_y = 5.0f;
    inline bool  aim_deadzone_enabled = false;
    inline int   aim_deadzone_min = 3;
    inline int   aim_deadzone_max = 10;
    inline bool  aim_show_fov = false;
    inline int   aim_fov_style = 0;
    inline bool  vis_team_check = false;
    inline float aim_fov_color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
    inline bool  aim_fov_outline = true;
    inline float aim_fov_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline bool  aim_fov_fill = false;
    inline float aim_fov_fill_color[4] = { 1.0f, 1.0f, 1.0f, 0.15f };

    inline bool  aim_autoshoot = false;
    inline int   aim_autoshoot_key = 0;
    inline int   aim_autoshoot_key_mode = 2;
    inline float aim_autoshoot_delay = 50.0f;

    inline bool  aim_team_check = false;
    inline bool& team_check = aim_team_check;
    inline bool  aim_visible_check = false;
    inline bool  aim_magicbullet = false;
    inline bool  aim_tracer = false;
    inline float aim_tracer_color[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    inline bool  aim_tracer_outline = true;
    inline float aim_tracer_outline_color[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
    inline float aim_tracer_thickness = 1.5f;
    inline bool  aim_health_check = false;
    inline float aim_health_value = 100.0f;
    inline bool  aim_distance_check = false;
    inline float aim_distance_value = 500.0f;

    inline bool  walkspeed_enabled = false;
    inline float walkspeed_value = 16.0f;
    inline int   walkspeed_key = 0;
    inline int   walkspeed_key_mode = 2;

    inline bool  jumppower_enabled = false;
    inline float jumppower_value = 50.0f;
    inline int   jumppower_key = 0;
    inline int   jumppower_key_mode = 2;

    inline bool  fov_enabled = false;
    inline float fov_value = 90.0f;
    inline int   fov_key = 0;
    inline int   fov_key_mode = 2;

    inline bool  noclip_enabled = false;
    inline int   noclip_key = 0;
    inline int   noclip_key_mode = 2;

    inline bool  freecam_enabled = false;
    inline int   freecam_key = 0;
    inline int   freecam_key_mode = 2;
    inline float freecam_speed = 50.0f;
    inline float freecam_sensitivity = 0.0025f;

    inline bool  hipheight_enabled = false;
    inline float hipheight_value = 2.1f;
    inline int   hipheight_key = 0;
    inline int   hipheight_key_mode = 2;

    inline bool  infjump_enabled = false;
    inline int   infjump_key = 0;
    inline int   infjump_key_mode = 2;

    inline bool  hitsound_enabled = false;
    inline int   hitsound_selected = 0;
    inline int   hitsound_mode = 0;
    inline float hitsound_volume = 100.0f;

    inline bool  time_enabled = false;
    inline float time_value = 14.0f;

    inline bool  world_fog_enabled = false;
    inline float world_fog_color[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
    inline float world_fog_start = 0.0f;
    inline float world_fog_end = 500.0f;

    inline bool  world_exposure_enabled = false;
    inline float world_exposure_value = 0.0f;

    inline void disable_all()
    {
        box_enabled = false;
        skeleton_enabled = false;
        health_enabled = false;
        name_enabled = false;
        headdot_enabled = false;
        distance_enabled = false;
        tool_enabled = false;
        flags_enabled = false;
        flags_team = false;
        flags_state = false;
        flags_health = false;
        tracer_enabled = false;
        oof_enabled = false;
        aim_enabled = false;
        aim_smoothing_enabled = false;
        aim_deadzone_enabled = false;
        aim_show_fov = false;
        aim_fov_fill = false;
        aim_fov_outline = false;
        aim_autoshoot = false;
        aim_team_check = false;
        aim_visible_check = false;
        aim_magicbullet = false;
        aim_tracer = false;
        aim_tracer_outline = false;
        aim_health_check = false;
        aim_distance_check = false;
        walkspeed_enabled = false;
        jumppower_enabled = false;
        fov_enabled = false;
        noclip_enabled = false;
        freecam_enabled = false;
        hipheight_enabled = false;
        infjump_enabled = false;
        hitsound_enabled = false;
        time_enabled = false;
        world_fog_enabled = false;
        world_exposure_enabled = false;
    }

    inline struct SavedFeatures
    {
        bool valid = false;
        bool box = false;
        bool skeleton = false;
        bool health = false;
        bool name = false;
        bool headdot = false;
        bool distance = false;
        bool tool = false;
        bool flags = false;
        bool flags_team = false;
        bool flags_state = false;
        bool flags_health = false;
        bool tracer = false;
        bool oof = false;
        bool aim = false;
        bool aim_smoothing = false;
        bool aim_deadzone = false;
        bool aim_show_fov = false;
        bool aim_fov_fill = false;
        bool aim_fov_outline = false;
        bool aim_autoshoot = false;
        bool aim_team_check = false;
        bool aim_visible_check = false;
        bool aim_magicbullet = false;
        bool aim_tracer = false;
        bool aim_tracer_outline = false;
        bool aim_health_check = false;
        bool aim_distance_check = false;
        bool walkspeed = false;
        bool jumppower = false;
        bool fov = false;
        bool noclip = false;
        bool freecam = false;
        bool hipheight = false;
        bool infjump = false;
        bool hitsound = false;
        bool time = false;
        bool world_fog = false;
        bool world_exposure = false;
    } saved;

    inline void push_state()
    {
        if (saved.valid) return;
        saved.valid = true;
        saved.box = box_enabled;
        saved.skeleton = skeleton_enabled;
        saved.health = health_enabled;
        saved.name = name_enabled;
        saved.headdot = headdot_enabled;
        saved.distance = distance_enabled;
        saved.tool = tool_enabled;
        saved.flags = flags_enabled;
        saved.flags_team = flags_team;
        saved.flags_state = flags_state;
        saved.flags_health = flags_health;
        saved.tracer = tracer_enabled;
        saved.oof = oof_enabled;
        saved.aim = aim_enabled;
        saved.aim_smoothing = aim_smoothing_enabled;
        saved.aim_deadzone = aim_deadzone_enabled;
        saved.aim_show_fov = aim_show_fov;
        saved.aim_fov_fill = aim_fov_fill;
        saved.aim_fov_outline = aim_fov_outline;
        saved.aim_autoshoot = aim_autoshoot;
        saved.aim_team_check = aim_team_check;
        saved.aim_visible_check = aim_visible_check;
        saved.aim_magicbullet = aim_magicbullet;
        saved.aim_tracer = aim_tracer;
        saved.aim_tracer_outline = aim_tracer_outline;
        saved.aim_health_check = aim_health_check;
        saved.aim_distance_check = aim_distance_check;
        saved.walkspeed = walkspeed_enabled;
        saved.jumppower = jumppower_enabled;
        saved.fov = fov_enabled;
        saved.noclip = noclip_enabled;
        saved.freecam = freecam_enabled;
        saved.hipheight = hipheight_enabled;
        saved.infjump = infjump_enabled;
        saved.hitsound = hitsound_enabled;
        saved.time = time_enabled;
        saved.world_fog = world_fog_enabled;
        saved.world_exposure = world_exposure_enabled;
    }

    inline bool restore_state()
    {
        if (!saved.valid) return false;
        bool any = saved.box || saved.skeleton || saved.health || saved.name
            || saved.headdot || saved.distance || saved.tool || saved.flags
            || saved.tracer || saved.oof || saved.aim
            || saved.aim_show_fov || saved.aim_autoshoot || saved.aim_tracer
            || saved.walkspeed || saved.jumppower || saved.fov || saved.noclip
            || saved.freecam || saved.hipheight || saved.infjump || saved.hitsound
            || saved.time || saved.world_fog || saved.world_exposure;
        box_enabled = box_enabled || saved.box;
        skeleton_enabled = skeleton_enabled || saved.skeleton;
        health_enabled = health_enabled || saved.health;
        name_enabled = name_enabled || saved.name;
        headdot_enabled = headdot_enabled || saved.headdot;
        distance_enabled = distance_enabled || saved.distance;
        tool_enabled = tool_enabled || saved.tool;
        flags_enabled = flags_enabled || saved.flags;
        flags_team = flags_team || saved.flags_team;
        flags_state = flags_state || saved.flags_state;
        flags_health = flags_health || saved.flags_health;
        tracer_enabled = tracer_enabled || saved.tracer;
        oof_enabled = oof_enabled || saved.oof;
        aim_enabled = aim_enabled || saved.aim;
        aim_smoothing_enabled = aim_smoothing_enabled || saved.aim_smoothing;
        aim_deadzone_enabled = aim_deadzone_enabled || saved.aim_deadzone;
        aim_show_fov = aim_show_fov || saved.aim_show_fov;
        aim_fov_fill = aim_fov_fill || saved.aim_fov_fill;
        aim_fov_outline = aim_fov_outline || saved.aim_fov_outline;
        aim_autoshoot = aim_autoshoot || saved.aim_autoshoot;
        aim_team_check = aim_team_check || saved.aim_team_check;
        aim_visible_check = aim_visible_check || saved.aim_visible_check;
        aim_magicbullet = aim_magicbullet || saved.aim_magicbullet;
        aim_tracer = aim_tracer || saved.aim_tracer;
        aim_tracer_outline = aim_tracer_outline || saved.aim_tracer_outline;
        aim_health_check = aim_health_check || saved.aim_health_check;
        aim_distance_check = aim_distance_check || saved.aim_distance_check;
        walkspeed_enabled = walkspeed_enabled || saved.walkspeed;
        jumppower_enabled = jumppower_enabled || saved.jumppower;
        fov_enabled = fov_enabled || saved.fov;
        noclip_enabled = noclip_enabled || saved.noclip;
        freecam_enabled = freecam_enabled || saved.freecam;
        hipheight_enabled = hipheight_enabled || saved.hipheight;
        infjump_enabled = infjump_enabled || saved.infjump;
        hitsound_enabled = hitsound_enabled || saved.hitsound;
        time_enabled = time_enabled || saved.time;
        world_fog_enabled = world_fog_enabled || saved.world_fog;
        world_exposure_enabled = world_exposure_enabled || saved.world_exposure;
        saved.valid = false;
        return any;
    }
}
