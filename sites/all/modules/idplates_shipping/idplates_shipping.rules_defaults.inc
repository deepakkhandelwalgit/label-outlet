<?php

/**
 * Implements hook_default_rules_configuration().
 */
function idplates_shipping_default_rules_configuration() {

  $items = array();
  $items['rules_idplates_continental_us'] = entity_import('rules_config', '{ "rules_continental_us" : {
    "LABEL" : "Continental US",
    "PLUGIN" : "and",
    "OWNER" : "rules",
    "REQUIRES" : [ "commerce_order" ],
    "AND" : [
      { "commerce_order_compare_address" : {
          "commerce_order" : [ "site:current-cart-order" ],
          "address_field" : "commerce_customer_shipping|commerce_customer_address",
          "address_component" : "country",
          "value" : "US"
        }
      },
      { "NOT commerce_order_compare_address" : {
          "commerce_order" : [ "site:current-cart-order" ],
          "address_field" : "commerce_customer_shipping|commerce_customer_address",
          "address_component" : "administrative_area",
          "operator" : "is one of",
          "value" : "HI\r\nAK"
        }
      }
    ]
  }
}');
  return $items;
}