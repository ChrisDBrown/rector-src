<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrNotConst
{
    const BUNDLE = 'value';

    public function run()
    {
        $isNotMatch = substr($haystack, -5) !== self::BUNDLE;

        $isNotMatch = self::BUNDLE !== substr($haystack, -5);
    }
}

?>
-----
<?php

namespace Rector\Tests\Php80\Rector\Identical\StrEndsWithRector\Fixture;

class SubstrNotConst
{
    const BUNDLE = 'value';

    public function run()
    {
        $isNotMatch = !str_ends_with($haystack, self::BUNDLE);

        $isNotMatch = !str_ends_with($haystack, self::BUNDLE);
    }
}

?>
