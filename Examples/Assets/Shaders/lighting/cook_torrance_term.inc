#ifndef COOK_TORRANCE_TERM
#define COOK_TORRANCE_TERM

float4 cook_torrance(
            in float3 normal,
            in float3 viewer,
            in float3 light, float roughness_value, float ref_at_norm_incidence, float3 cSpecular, float3 cDiffuse)
{    
    // Compute any aliases and intermediary values
    // -------------------------------------------
    float3 half_vector = normalize( light + viewer );
    float NdotL        = saturate( dot( normal, light ) );
    float NdotH        = max( dot( normal, half_vector ) , 1.0e-7);
    float NdotV        = saturate( dot( normal, viewer ) );
    float VdotH        = saturate( dot( viewer, half_vector ) );
    float r_sq         = roughness_value * roughness_value;
 
 
 
    // Evaluate the geometric term
    // --------------------------------
    float geo_numerator   = 2.0f * NdotH;
    float geo_denominator = VdotH;
 
    float geo_b = (geo_numerator * NdotV ) / geo_denominator;
    float geo_c = (geo_numerator * NdotL ) / geo_denominator;
    float geo   = min( 1.0f, min( geo_b, geo_c ) );
 
 
 
    // Now evaluate the roughness term
    // -------------------------------
    float roughness;
    float roughness_a = 1.0f / ( 4.0f * r_sq * pow( NdotH, 4 ) );
    float roughness_b = NdotH * NdotH - 1.0f;
    float roughness_c = r_sq * NdotH * NdotH;
    roughness = roughness_a * exp( roughness_b / roughness_c );


    // Next evaluate the Fresnel value
    // -------------------------------
    float fresnel = pow( 1.0f - VdotH, 5.0f );
    fresnel *= ( 1.0f - ref_at_norm_incidence );
    fresnel += ref_at_norm_incidence;
 
 
 
    // Put all the terms together to compute
    // the specular term in the equation
    // -------------------------------------
    float3 Rs_numerator   = ( fresnel * geo * roughness );
    float Rs_denominator  = max(1.0e-7, NdotV * NdotL);
    float3 Rs             = Rs_numerator/ Rs_denominator;
 
 
 
    // Put all the parts together to generate
    // the final colour
    // --------------------------------------


	Rs = max(0, Rs);
    float3 final = max(0.0f, NdotL) *cDiffuse + (1 * Rs );
 
    // Return the result
    // -----------------
    return float4( final, 1.0f );
}

#endif